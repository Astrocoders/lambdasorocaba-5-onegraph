type route =
  | Login
  | Home
  | Hype;

let routeFromPath = (url: ReasonReactRouter.url) =>
  switch (url.path) {
  | ["home"] => Home
  | ["hype"] => Hype
  | ["login"] => Login
  | _ => Home
  };
let routeToPath = (route: route) =>
  switch (route) {
  | Home => "/home"
  | Hype => "/hype"
  | Login => "/login"
  };
