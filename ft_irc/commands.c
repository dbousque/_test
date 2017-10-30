

/*
 * If a NICK message arrives at a server which already knows about an
 * identical nickname for another client, a nickname collision occurs.
 * As a result of a nickname collision, all instances of the nickname
 * are removed from the server's database, and a KILL command is issued
 * to remove the nickname from all other server's database. If the NICK
 * message causing the collision was a nickname change, then the
 * original (old) nick must be removed as well.
 */

void	nick(connection, char *new_name)
{
	if (new_name already exists)
	{
		delete all instances of the name (including friends)
		if connection->nickname exists
			delete all instances of it as well
	}
}