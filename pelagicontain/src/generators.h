/*
 *   Copyright (C) 2014 Pelagicore AB
 *   All rights reserved.
 */
#ifndef GENERATORS_H
#define GENERATORS_H

#include <string>

/*! \brief  Generator functions
 *  \file   generators.h
 *
 *  Various helper functions for generating things such as network interface
 *  names, IP addresses and container names. By using these functions, unique
 *  names are ensured
 */

/*! \brief Generate a network interface name
 *
 * This will generate a network interface name which can be used to create new
 * virtual network interfaces
 *
 * \param ip_addr_net The network portion of the IP address for the new network
 *                    interface. Used to generate a descriptive name.
 * \return A unique network interface name
 * \return NULL upon error
 */
std::string gen_net_iface_name(const char *ip_addr_net);

/*!  \brief Generate a gateway address
 *
 * Given the network portion of an IP address, this will output a suggested
 * gateway IP address.
 *
 * \return A gateway IP address
 * \return NULL upon error
 */
char *gen_gw_ip_addr (char *ip_addr_net);

/*! \brief Generate an IP address
 *
 * Calling this function will generate a new IP address. A counter is kept in
 * /tmp to minimize the risk of collissons
 *
 * \param ip_addr_net A 24 bit network portion of an IP address
 * \return A string representing an IP address
 */
std::string gen_ip_addr (const char *ip_addr_net);

/*! \brief Generate a container name
 *
 * Generate a container name based on the current time in milliseconds
 *
 * \return name upon success
 * \return NULL upon failure
 */
std::string gen_ct_name();

#endif /* GENERATORS_H */