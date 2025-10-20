1 → Main Loop

. Start and maintain the server with the main loop;

. Monitor multiple sockets with poll();

. Accept new connections (accept()) and register them in the loop (one per client);

. Read/write data from those file descriptors.





2 → Connection Management

. Control the lifecycle of each connected client;

. Read requests from client sockets (raw HTTP requests) and parse them into the HttpRequest class;

. Decide whether the request maps to a static file, a CGI, or an error;

. Write back a properly formatted HTTP response (HttpResponse).





3 → CGI Integration

. When a request matches a route configured for CGI, delegate execution to the CGI module;

. Collect the CGI response and transform it into a valid HttpResponse;

. Send the formatted response back to the client.





4 → HTTP Response Generation

. Handle basic requests (GET, POST, DELETE);

. Implement proper error handling (404, 405, 413, 500, etc.);

. Respect mandatory HTTP headers;

. Serve static files when requested.

//responses must comply with HTTP/1.1 formatting — status line, headers, CRLF separation, body.





5 → Timeout and Robustness Management

. Avoid leaving connections hanging indefinitely;

. Close sockets properly when clients disconnect or on error;

. No memory leaks :3
