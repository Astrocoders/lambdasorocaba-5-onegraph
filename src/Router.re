type route =
  | Home
  | Hype;

let routeFromPath = (url: ReasonReactRouter.url) =>
  switch (url.path) {
  | ["home"] => Home
  | ["hype"] => Hype
  | _ => Home
  };
let routeToPath = (route: route) =>
  switch (route) {
  | Home => "/home"
  | Hype => "/hype"
  };
