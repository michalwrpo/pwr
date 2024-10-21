# World Wide Web

- Invented in 1989


## Hypertext Transfer Protocol

- Developed for a simple exchange of static pages
- It is a stateless protocol
- There is no security provided

### Cookies

- It's a layer on top of HTTPS which adds sessions

## Web timeline

- In the beginning consisted only of static pages
- Then dynamic server-side web applications
- Up to current web applicaitons runing mostly in the web browser
  - Progressive Web Apps

**PC Era**
- Email
- FTP

**WWW**
- HTTPS
- HTML
- Online dataase
- File server
- Website

**Social Web**
- JS
- Flash
- XML
- Social Networking
- Collaboration
- Weblogs

**Semantic Web**
- RDF
- OWL
- Atom
- Semantic Search
- Semantic DBs
- Widgets

**MetaWeb**
- Distributed Search
- Personal Intelligence
- Agents

## Web applications

- Run in browser
- Almost excusively Client-Server architecture
- UI is implemented in web technologies
- Big boom in the last 10 years
- Critical application
  - Financial applications
  - Internal systems
- Inherits all the web security issues

## Securing the web

- Data protection en route (between the user and the web server)
  - Confidentiality, integrity
- Mitigation of webserver spoofing
  - Authencitation (one way)
- Cryptography
  - Transformation of plaintext to ciphertext and back

### Asymmetric cryptography

- Uses two distinct keys
  - Private - known only to the owner, if leaked the security is breached
  - Public - known to everyone, used to send private messages to the owner or verify his messages
- One key is used for encryption, the other for decryption
  - Contenct protection: lock public, unlock private
  - Digital signature: lock private, unlock public

### Kerckhoff's principle

"The encryption procedure must not require secrecy and it must always be assumed that it can easily fall into enemy hands."

The security have to depend only on the secrecy of the key.

### Transport Layer Security (TLS)

- Based on SSL - Secure Sockets Layer, therefore SSL/TLS (the same basically)
- Protocol for data transfer protection on the web
  - HTTPS - Hypertext Transfer Protocol Secure
  - Asymmetric handshake + symmetric encryption
- Server is authenticated based on it's certificate

### Certificate

- How do we verify certificate ownership?
  - Thanks to the properties of asymmetric cryptography, we verify that the counterparty owns the private key to the public key from the certificate.
- How do we verify the validity of the certificate?
  - We trust the thrid part - Certification Authorities


### Penetration testing

- Security testing of application on infrastructure with a simulated cyberattack
  - Blackbox - the adversary has no prior knowledge about the internal structure of the system
  - Whitebox - the adversary has access to all the information about the system (including the source codes)
- Penetration testing must ALWAYS be approved by the system administrator. Failure to do so exposes the tester to persecution under the local law.

### Open Web Application Security Project

- Web security monitoring
- https://www.owasp.org

### Path traversal

- The server usually publishes only certain subset of files
- If the adversary guesses the correct file path and the server is misconfigurated, the adversary may gain unauthorised access

### Path traversal mitigation

- Chroot jail
  - The web server cannot access other files than required for its run
- Proper web server configuration
  - Prohibited access to the sensitive folders
- Use the whitelisting and don't allow user-set custom paths
  - The user is restricted to predetermined set of server-side defined options
- User input sanitization

### SQL injection

- Virtually all (web) applications manage data for their operations
- Database = specialised data store
- Unified data access inferface - Structured Query Language
 
### SQL injection mitigation

- Prepared queries 
```sql
PREPARE query 'FROM SELECT * FROM users WHERE username=? AND password=?';
EXECUTE query WITH $user $passwd 
```

### Cookie stealing

- Cookies are just plaintext files
  - Anyone can capture them
  - Header cookie
- Secure flag
  - Sent only over HTTPS

### Cross-Site Scripting (XSS)

- The concurrent websites perform a diverse set of actions
- XSS = injection of executable code into the website
  - Most commonly via unprotected user input
  - Reflected x Stored
- What can we achieve by it?
  - Theft of sensitive data
  - Rogue advertising
  - Redirection to the phishing site
  - Cryptocurrency mining

### Protection against XSS

- Content security policy (CSP)
  - Special HTTP header
  - Executables are limited to the specified domains
- Same-Origin policy
  - Enforced by the browsers
  - The data is accessible only from the same **[ protocol, domain, port ]**

### Zed Attack Proxy

- One of the many automation tools for web application pentesting
- Developed by OWASP
- https://www.zaproxy.org/

#### "Playing around" options

- Online applications / environments
  - HackThisSite - www.hackthissite.org
  - Try Hack Me - tryhackme.com
  - Hack the Box