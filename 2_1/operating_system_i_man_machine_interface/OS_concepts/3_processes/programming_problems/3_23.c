/* 3.23
 * Section 3.8.1 describes certain port numbers as being well known—that
 * is, they provide standard services. Port 17 is known as the quote-of-the-
 * day service. When a client connects to port 17 on a server, the server
 * responds with a quote for that day.
 * 
 * Modify the date server shown in Figure 3.27 so that it delivers a quote
 * of the day rather than the current date. The quotes should be printable
 * ASCII characters and should contain fewer than 512 characters, although
 * multiple lines are allowed. Since these well-known ports are reserved
 * and therefore unavailable, have your server listen to port 6017. The date
 * client shown in Figure 3.28 can be used to read the quotes returned by
 * your server.
 */