let hypeDeps = [|"react", "react-dom", "graphql", "reason-react"|];

let vcNaoEhHypeBro = [|"jquery", "angular", "handlebars", "axios"|];

module Query = [%graphql
  {|
  query HomeQuery($name: String, $runQuery: Boolean!) {
    npm @include(if: $runQuery) {
      package(name:$name) {
        description
        repository {
          sourceRepository {
            ... on GitHubRepository {
              stargazers {
                totalCount
              }
            }
          }
        }
      }
    }
  }
|}
];

module QueryContainer = ReasonApollo.CreateQuery(Query);

let countHype = (~dependencies) => {
  dependencies->Belt.Array.map(((name, _version)) => {
    let variables = Query.make(~name, ~runQuery=true, ())##variables;

    GraphQLClient.instance##query({ "query": QueryContainer.gql(. Query.query), "variables": variables  });
  })
  |> Js.Promise.all
  |> Js.Promise.then_(packages =>
       packages->Belt.Array.reduce(0, (acc, result) =>
         switch (result->ReasonApolloQuery.dataGet->Js.Nullable.toOption->Belt.Option.map(Query.parse)) {
         | Some(data) =>
           acc
           + data##npm
             ->Belt.Option.flatMap(npm => npm##package)
             ->Belt.Option.flatMap(package => package##repository)
             ->Belt.Option.flatMap(repository => repository##sourceRepository)
             ->Belt.Option.map(repository =>
                 switch (repository) {
                 | `GitHubRepository(repository) =>
                   repository##stargazers##totalCount
                 }
               )
             ->Belt.Option.getWithDefault(0)
         | None => acc
         }
       )
       |> Js.Promise.resolve
     );
};

[@react.component]
let make = () => {
  let (hypeCount, setHypeCount) = React.useState(() => 0);
  let inputRef = React.useRef(None);
  let (dependencies, setDependencies) = React.useState(() => None);

  let handleInputRef =
    React.useCallback0(input =>
      inputRef->React.Ref.setCurrent(Js.Nullable.toOption(input))
    );

  let handleFileChange = _ => {
    switch (inputRef->React.Ref.current) {
    | Some(input) =>
      ReactDOMRe.domElementToObj(input)##files[0]
      |> FileReader.File.toString
      |> Js.Promise.then_(res => {
           let parsedDeps = res->Js.Json.parseExn->PackageJson.getDependencies;

           let dependencies = Js.Nullable.toOption(parsedDeps);
           setDependencies(_ => dependencies);

           countHype(
             ~dependencies=Belt.Option.getWithDefault(dependencies, [||]),
           )
           |> Js.Promise.then_(hypeCount => {
                setHypeCount(_ => hypeCount);
                Js.Promise.resolve();
              });
         })
      |> ignore
    | None => ()
    };
  };

  <>
    <div>
      <label> {React.string("Select a package.json")} </label>
      <input
        ref={ReactDOMRe.Ref.callbackDomRef(handleInputRef)}
        type_="file"
        accept="application/json"
        onChange=handleFileChange
      />
    </div>
    {switch (dependencies) {
     | Some(dependencies) =>
       <>
         <h1> {React.string({j|Seu hype count é $hypeCount |j})} </h1>
         {switch (hypeCount) {
          | 0 => <h1> {React.string({j|Você não é hype, bro|j})} </h1>
          | _ as n =>
            n > 10000
              ? <h1> {React.string({j|Você é hype, bro|j})} </h1>
              : <h1> {React.string({j|Você é quase hype, bro|j})} </h1>
          }}
         <ul>
           {dependencies
            ->Belt.Array.map(((name, _version)) =>
                <li> {React.string(name)} </li>
              )
            ->React.array}
         </ul>
       </>
     | None => React.string("Escolha um package.json, bro")
     }}
  </>;
};
