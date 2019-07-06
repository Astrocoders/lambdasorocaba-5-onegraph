type t = Js.Json.t;

let getDependencies: t => Js.Nullable.t((string, string)) = [%raw {|(packageJson) => {
  if(!packageJson.dependencies) return null
  return Object.keys(packageJson.dependencies).map(key => [key, packageJson.dependencies[key]])
}
|}]
