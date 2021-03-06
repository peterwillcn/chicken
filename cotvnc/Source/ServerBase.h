//
//  ServerFromPrefs.h
//  Chicken of the VNC
//
//  Created by Jared McIntyre on Sat Jan 24 2004.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#import <Foundation/Foundation.h>
#import "IServerData.h"

#define PORT_BASE 5900

@class Profile;

/// This represents all the data and settings needed to connect to a VNC server.
@interface ServerBase : NSObject <IServerData> {
	NSString* _host;
	NSString* _password;
	int       _port;
	bool      _shared;
	bool      _fullscreen;
	bool      _viewOnly;	
    Profile   *_profile;

    NSString  *_sshHost;
    in_port_t _sshPort; //!< 0 means use default port
    NSString  *_sshUser;
}

- (instancetype)init NS_DESIGNATED_INITIALIZER;

- (bool)doYouSupport: (SUPPORT_TYPE)type;

@property (readonly, copy) NSString *name;
- (NSString*)name;
@property (nonatomic, copy) NSString *host;
- (NSString*)password;
@property (readonly) BOOL rememberPassword;
@property (readwrite) int port;
@property (readwrite) bool shared;
- (bool)fullscreen;
- (bool)viewOnly;
- (Profile *)profile;
@property (readonly) bool addToServerListOnConnect;

@property (readwrite, copy) NSString *sshHost;
- (NSString *)sshHost;

/// 0 means use default port
@property (readonly) in_port_t sshPort;
- (in_port_t)sshPort;

@property (readonly, copy) NSString *sshUser;
- (NSString *)sshUser;
@property (readwrite, copy) NSString *sshString;
- (NSString *)sshString;

- (void)setHost: (NSString*)host;
- (BOOL)setHostAndPort: (NSString*)host;
@property (readwrite, copy) NSString *password;
- (void)setPassword: (NSString*)password;
- (void)setDisplay: (int)display;
- (void)setShared: (bool)shared;
- (void)setPort: (int)port;
@property (readwrite) bool fullscreen;
- (void)setFullscreen: (bool)fullscreen;
@property (readwrite) bool viewOnly;
- (void)setViewOnly: (bool)viewOnly;
@property (readwrite, strong) Profile *profile;
- (void)setProfile: (Profile *)profile;
- (void)setProfileName: (NSString *)profileName;
- (void)setSshHost:(NSString *)sshHost;
- (void)setSshString:(NSString *)str;
- (void)setSshTunnel:(BOOL)enable;

- (void)copyServer: (id<IServerData>)server;

@end
