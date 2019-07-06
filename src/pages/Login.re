let handleLogIn = (auth, logIn) => {
  Js.Promise.(
    OneGraphAuth.(
      auth
      |> login(_, "github")
      |> then_(() => isLoggedIn(auth, "github"))
      |> then_(isLoggedIn => {
           if (isLoggedIn) {
             logIn();
           };
           resolve();
         })
      |> catch(err => resolve(Js.log(err)))
      |> ignore
    )
  );
};

[@react.component]
let make = (~auth, ~logIn) => {
  <div>
    <button onClick={(_) => handleLogIn(auth, logIn)}>
      {React.string("Login to GitHub Account")}
    </button>
  </div>;
};
