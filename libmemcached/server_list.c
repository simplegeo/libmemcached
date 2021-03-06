/* LibMemcached
 * Copyright (C) 2006-2010 Brian Aker
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license.  See
 * the COPYING file in the parent directory for full text.
 *
 * Summary: 
 *
 */


#include "common.h"

memcached_server_st *memcached_server_list_append_with_weight(memcached_server_st *ptr,
                                                              const char *hostname, in_port_t port,
                                                              uint32_t weight,
                                                              memcached_return_t *error)
{
  unsigned int count;
  memcached_server_instance_st *new_host_list;

  if (hostname == NULL || error == NULL)
    return NULL;

  if (! port)
    port= MEMCACHED_DEFAULT_PORT;

  /* Increment count for hosts */
  count= 1;
  if (ptr != NULL)
  {
    count+= memcached_servers_count(ptr);
  }

  new_host_list= (memcached_server_instance_st *)realloc(ptr, sizeof(memcached_server_instance_st) * count);
  if (!new_host_list)
  {
    *error= MEMCACHED_MEMORY_ALLOCATION_FAILURE;
    return NULL;
  }

  /* TODO: Check return type */
  memcached_server_create_with(NULL, &new_host_list[count-1], hostname, port, weight, MEMCACHED_CONNECTION_TCP);

  /* Backwards compatibility hack */
  memcached_servers_set_count(new_host_list, count);

  *error= MEMCACHED_SUCCESS;
  return new_host_list;
}

memcached_server_st *memcached_server_list_append(memcached_server_st *ptr,
                                                  const char *hostname, in_port_t port,
                                                  memcached_return_t *error)
{
  return memcached_server_list_append_with_weight(ptr, hostname, port, 0, error);
}
