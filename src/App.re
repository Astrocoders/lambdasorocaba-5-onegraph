[@react.component]
let make = () =>
  <div>
    {switch (Router.routeFromPath(ReasonReactRouter.useUrl())) {
     | Login => <Login auth=GraphQLClient.auth logIn=ignore />
     | Home => <Home />
     | Hype => <Hype />
     }}
  </div>;
