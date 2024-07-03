<pre>
                ___
               /   |  ____  ____  ____  __  ______  ________  _____
              / /| | / __ \/ __ \/ __ \/ / / / __ \/ ___/ _ \/ ___/
             / ___ |/ / / / / / / /_/ / /_/ / / / / /__/  __/ /
            /_/  |_/_/ /_/_/ /_/\____/\__,_/_/ /_/\___/\___/_/
                                                                         
                                version 1.5
                   Copyright (c) 2021-24 Elwynor Technologies

</pre>

## WHAT IS ANNOUNCER?

 Announcer is a basic utility that gives you the ability to send global
 broadcasts to users you select by key at intervals you choose. This version
 supports one broadcast message. You will definitely want to edit this message
 right away in CNF.

 You control who gets the broadcast by key; the default is that only DEMO users
 get them, but if you change the key to SUPER for example, everyone but those
 with the SUPER key will get the broadcasts. You also choose how many seconds
 come between broadcasts. All of this is configurable in CNF.

## INSTALLATION AND CONFIGURATION

 Simply unzip the archive to your BBS server directory, add 
 it to your menu, configure the MSG file to your liking, and start 
 the BBS!  It's that easy! 

 In LEVEL3, you can set what key is required to NOT be pestered.
 
 In LEVEL4, you can set the interval in seconds between pesters, whether the
 message beeps the user, and whether or not to pester users in the Editor.
 
 In LEVEL6, you can configure the pestering message!
 
## MODULE HISTORY
 
 Announcer was written in January 1995 by "Easy Ed" Erdman of EzSoft. The
 module was available as a free module up through Worldgroup 3.0. 
 
 EzSoft was acquired by AdventureComm, which was acquired by Elwynor 
 Technologies in 2004.

 Elwynor Technologies ported the module to Worldgroup 3.2 in May 2021, and
 converted it to Major BBS V10 in July 2024.
 
## LICENSE

 This project is licensed under the AGPL v3. Additional terms apply to 
 contributions and derivative projects. Please see the LICENSE file for 
 more details.

## CONTRIBUTING

 We welcome contributions from the community. By contributing, you agree to the
 terms outlined in the CONTRIBUTING file.

## CREATING A FORK

 If you create an entirely new project based on this work, it must be licensed 
 under the AGPL v3, assign all right, title, and interest, including all 
 copyrights, in and to your fork to Rick Hadsall and Elwynor Technologies, and 
 you must include the additional terms from the LICENSE file in your project's 
 LICENSE file.

## COMPILATION

 This is a Worldgroup 3.2 / Major BBS v10 module. It's compiled using Borland
 C/C++ 5.0 for Worldgroup 3.2. If you have a working Worldgroup 3.2 development
 kit, a simple "make -f ELWDMPST" should do it! For Major BBS v10, import this
 project folder in the isv/ subtree of Visual Studio 2022, right click the
 project name and choose build! When ready to build for "release", ensure you
 are building for release.

## PACKING UP

 The DIST folder includes all of the items that should be packaged up in a 
 ELWDMPST.ZIP. When unzipped in a Worldgroup 3.2 or Major BBS V10 installation 
 folder, it "installs" the module.
