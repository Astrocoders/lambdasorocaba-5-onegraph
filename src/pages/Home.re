[@react.component]
let make = () => {
  let inputRef = React.useRef(None);
  let handleInputRef = React.useCallback0((input) => {
    inputRef->React.Ref.setCurrent(Js.Nullable.toOption(input))
  });
  let handleFileChange = (_) => {
    switch(inputRef->React.Ref.current) {
      | Some(input) => {
        ReactDOMRe.domElementToObj(input)##files[0]
          |>FileReader.File.toString
          |>Js.Promise.then_(res => Js.log(res) |> Js.Promise.resolve)
          |>ignore
        }
      | None => ()
    }
  };

  <div>
    <label>
      <input ref={ReactDOMRe.Ref.callbackDomRef(handleInputRef)} type_="file" accept="application/json" onChange=handleFileChange/>
    </label>
  </div>
}
