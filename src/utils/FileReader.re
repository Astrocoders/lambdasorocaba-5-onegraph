type t;
type event = {. "target": {. "result": string}};

[@bs.new] external make: unit => t = "FileReader";

[@bs.send]
external addEventListener: (t, string, event => unit) => unit =
  "addEventListener";
[@bs.send]
external readAsBinaryString: (t, event => unit) => unit = "readAsBinaryString";

module File = {
  let toString = file => {
    Js.Promise.make((~resolve, ~reject as _) => {
      let fileReader = make();

      fileReader->addEventListener("load", event =>
        resolve(. event##target##result)
      );

      fileReader->readAsBinaryString(file);
    });
  };
};
