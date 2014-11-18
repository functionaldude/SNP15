1.1 0x00008000 - bis limit
1.2 In unserem Fall 2 GB
1.3 Speicher wächst beim auffülen
1.4 Speicher schrumpft nicht

2.1 0xbf802f47 - bis limit
2.2 Limit: 8,3 MB
2.3 Speicher wächst beim auffülen
2.4 Speicher schrumpft nicht, sollte es aber normalerweise

3.1 0x00002010 - bis limit
3.2 Limit: 2 GB
3.3 Speicher wächst beim auffülen
3.4 <static variables when does memory usage decrease>

4.1 0x00300000 - bis limit
4.2 Limit: 2 GB
4.3 Speicher wächst beim auffülen
4.4 Speicher schrumpft bei "free"

5.1
5.2
5.3
5.4

6. Yes, it is a problem as there would be a memory leak.
7. The OS taes care of address conflicts.

