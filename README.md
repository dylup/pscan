# pscan - a TCP port scanner
Cycle 9

## Description
- Course: CSC842 Security Tool Development
- Developer: Dylan Johnson
- Language: C
- Scope: Offensive Security/Penetration Testing/Defensive Security/Networking

A C program to scan TCP ports on a given host. Useful for both offensive and defensive use cases. On the offensive side, it can be used to find open ports during the enumeration phase of a pentest, checking what ports are open that could potentially be running vulnerable services. On the defensive side, it can help a network administrator understand what things are running on the network, so they can start to determine what services could be removed/are unnecessary.

## Capabilities
pscan is able to take command line user input in the following format:

./pscan \<host\> \<startPort\> - \<endPort\>
  \<host\> is an IP address from 0.0.0.0 - 255.255.255.255
  \<startPort\> is a port from 1 - 65535
  \<endPort\> is a port starting at or equal to \<startPort\>
    
pscan then will loop through the port range provided and make a TCP socket connection to verify if the port is open or closed. The results are displayed at the end.

### Functionality
The primary function of this software is to determine the open ports on a given host.

## Future Work
Functionality should be added to check the status of UDP ports as well. Additionally, the ability to determine a specific service or state the commonly found service on given port should be added. Finally, rewriting the program to more quickly scan large amounts of ports/hosts would be ideal. At the moment, the program makes a full TCP connection to each port, and can take some time.

