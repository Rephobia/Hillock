## Intro
Hillock is application manager. Runned applications doesn't live longer than Hillock

## Build from sources

### Required
- **gcc** 8 or higher
- **cmake** 3.9 or higher
- **Qt5**

### Build
 
	cmake -Bbuild -H. && cmake --build build/
	
## OS support
Only Windows (child process tracking uses winapi)
Linux version WIP
