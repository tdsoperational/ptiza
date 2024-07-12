A keylogger written in C, its purpose being to test antiviruses to see if they intercept the logged keystrokes. Designed for a windows system, with no use of external libs.
The code itself isn't designed to evade in any way (for now)

**Disclaimer**

The author (Me, tdsoperational, known as tdsmental) is not responsible for any missuse.
As mentioned earlier, it is designed to test antivirus products, not missuse.

By missuse i mean using this code maliciously, or similiar.

Sincerely, tdsoperational.

**Functionality**
- Logs keystrokes without being too noisy
- Doesn't required admin perms
- Sends logged keystrokes to a domain assuming it has a route that accepts post requests
- Data sent is not encryped, working on making it encrypt data before being sent.
- 7.5 KB in size if packed with UPX.
- 11 KB in size if not packed at all

**Upcoming features**
- Obfuscation.
- Anti static analysis.
- Anti Behavioral analysis.
- A server so you don't need a goddamn domain.
- Persistance.
- Polymorphism upon execution.
- Randomized intervals of sending data, the upcoming server will be able to know when logged keystrokes will be received.
- Encrypting data before sending it.
