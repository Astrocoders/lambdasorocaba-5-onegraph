[@react.component]
let make = () =>
  <div>
    {switch (Router.routeFromPath(ReasonReactRouter.useUrl())) {
     | Home => <Home />
     | Hype => <Hype />
     }}
  </div>;
