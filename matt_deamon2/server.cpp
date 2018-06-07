

#include "Tintin_reporter.hpp"

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in6	sin;
	int					ret;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(AF_INET6, SOCK_STREAM, proto->p_proto);
	if (sock == -1)
		return (-1);
	ret = 0;
	setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, &ret, sizeof(int));
	sin.sin6_family = AF_INET6;
	sin.sin6_port = htons(port);
	sin.sin6_addr = in6addr_any;
	ret = bind(sock, (const struct sockaddr*)&sin, sizeof(sin));
	if (ret == -1)
		return (-1);
	ret = listen(sock, 4);
	if (ret == -1)
		return (-1);
	return (sock);
}