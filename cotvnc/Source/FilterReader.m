/* FilterReader.m created by helmut on 01-Nov-2000 */

/* Copyright (C) 1998-2000  Helmut Maierhofer <helmut.maierhofer@chello.at>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#import "FilterReader.h"
#import "EncodingReader.h"

@implementation FilterReader

- (id)initWithTarget: (TightEncodingReader *)aTarget
       andConnection: (RFBConnection *)aConnection
{
    if (self = [super init]) {
        target = aTarget;
        connection = aConnection;
    }
    return self;
}

/**
 * Begin using filter. When it has read enough, it should call
 * <code>[target filterInitDone]</code>. The default does this right
 * away.
 */
- (void)resetFilterForRect:(NSRect)rect
{
    [target filterInitDone];
}

@synthesize frameBuffer;

- (void)setFrameBuffer:(FrameBuffer*)aFrameBuffer
{
    frameBuffer = aFrameBuffer;
    bytesPerPixel = [frameBuffer tightBytesPerPixel];
}

/** Filter the data. Default is to return it unchanged. */
- (NSData*)filter:(NSData*)data rows:(unsigned)numRows
{
    return data;
}

- (unsigned)bitsPerPixel
{
    return bytesPerPixel * 8;
}

@synthesize bytesTransferred;

@end
