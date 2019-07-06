/* Create an InMemoryCache */
let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

/* Create an HTTP Link */
let httpLink =
  ApolloLinks.createHttpLink(
    ~uri=
      "https://serve.onegraph.com/dynamic?app_id=18704b93-e261-4332-b43c-90c50e9c2c2e",
    ~credentials="include",
    (),
  );

let auth = OneGraphAuth.newAuth(OneGraphAuth.config);

let authLink =
  ApolloLinks.createContextLink(
    OneGraphAuth.(
      () => {
        "headers": {
          "authorization": auth |> authHeaders |> authenticationHeaderGet,
        },
      }
    ),
  );

let instance =
  ReasonApollo.createApolloClient(
    ~link=ApolloLinks.from([|authLink, httpLink|]),
    ~cache=inMemoryCache,
    (),
  );
