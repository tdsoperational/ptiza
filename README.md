# ptiza

A keylogger written in C, its purpose being to test antiviruses to see if they intercept the logged keystrokes. Designed for a Windows system, with no use of external libraries. The code itself isn't designed to evade in any way (for now).

## Disclaimer

The author (Me, tdsoperational, known as tdsmental) is not responsible for any misuse. As mentioned earlier, it is designed to test antivirus products, not misuse.

By misuse, I mean using this code maliciously, or similar.

Sincerely, tdsoperational.

## Functionality

- Sends logged keystrokes to a domain assuming it has a route that accepts POST requests
- Data sent is encrypted, mostly to avoid AVs terminating the process
- 9 KB in size if packed with UPX
- 14 KB in size if not packed at all
- Anti-static analysis
- Anti-behavioral analysis
- Encrypts data before sending it with a random 3-character decryption key
- Just a little obfuscation
- Fallback C2
- Persistance (Reg key)

## Upcoming Features

- More evasion techniques
- More obfuscation

## Documentation

I've decided to test the keylogger I've made, both statically and dynamically.


Here is the VirusTotal report if you give a shit: [VirusTotal report](https://www.virustotal.com/gui/file/0d9ba751a47e198d4a270f29d031cb529ce3b8ea6e59957089d3c96e0e943275?nocache=1)


I've run the executable on my host machine. Kaspersky, my current AV with maxed-out settings, didn't give a shit apparently. But that's very likely a matter of time until they realize it is a keylogger.


That's it for now. Hopefully, you all enjoyed it!
