[@react.component]
let make = () =>
  <ReasonApollo.Provider client=GraphQLClient.instance>
    <div>
      {switch (Router.routeFromPath(ReasonReactRouter.useUrl())) {
       | Login =>
         <Login
           auth=GraphQLClient.auth
           logIn={() =>
             Router.Home |> Router.routeToPath |> ReasonReactRouter.push
           }
         />
       | Home => <Home />
       | Hype => <Hype />
       }}
    </div>
  </ReasonApollo.Provider>;
