A keylogger written in C, its purpose being to test antiviruses to see if they intercept the logged keystrokes. Designed for a windows system, with no use of external libs.
The code itself isn't designed to evade in any way (for now)

**Disclaimer**

The author (Me, tdsoperational, known as tdsmental) is not responsible for any missuse.
As mentioned earlier, it is designed to test antivirus products, not missuse.

By missuse i mean using this code maliciously, or similiar.

Sincerely, tdsoperational.

**Functionality**
- Logs keystrokes without being too noisy
- Doesn't require admin perms
- Sends logged keystrokes to a domain assuming it has a route that accepts post requests
- Data sent is not encryped, working on making it encrypt data before being sent.
- 8 KB in size if packed with UPX.
- 12 KB in size if not packed at all
- Anti static analysis.
- Anti Behavioral analysis.
- Encrypting data before sending it with a random 3 character key.
- Just a little obfuscation.

**Upcoming features**
- Persistance.
- Polymorphism upon execution.
- More evasion
- Global low level keyboard hook 

**Documentation**
I've decided to test the keylogger i've made, static and dynamic.
Speaking of static analysis, here are the VirusTotal link:
https://www.virustotal.com/gui/file/a4e82c076ee66cf63054fe3f3c0d98acca341958dbf679fd3c3dd88f647cfa40?nocache=1

Speaking of Behavioral analysis, i've ran the executable on my host machine. 
Kaspersky, my current AV with maxed out settings didn't give a shit apperantly.
But that is very likely a matter of time until they realize it is a keylogger.

That's it for now, hopefully something you all enjoyed!
