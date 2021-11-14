Search and delete this:

#include "check_server.h"

search and delete this too:

        TOKEN("server_key")
        {
            CCheckServer::Instance().AddServerKey(value_string);
            continue;
        }