//
//  Movist
//
//  Copyright 2006, 2007 Yong-Hoe Kim. All rights reserved.
//      Yong-Hoe Kim  <cocoable@gmail.com>
//
//  This file is part of Movist.
//
//  Movist is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 3 of the License, or
//  (at your option) any later version.
//
//  Movist is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#import "Movist.h"

#import <QuartzCore/QuartzCore.h>

enum {  // horizontal : exclusive
    OSD_HALIGN_LEFT                      = 1 << 0,
    OSD_HALIGN_CENTER                    = 1 << 1,
    OSD_HALIGN_RIGHT                     = 1 << 2,
};

enum {  // vertical : exclusive
    OSD_VALIGN_CENTER                    = 1 << 3,
    OSD_VALIGN_UPPER_FROM_MOVIE_TOP      = 1 << 4,
    OSD_VALIGN_LOWER_FROM_MOVIE_TOP      = 1 << 5,
    OSD_VALIGN_UPPER_FROM_MOVIE_BOTTOM   = 1 << 6,
    OSD_VALIGN_LOWER_FROM_MOVIE_BOTTOM   = 1 << 7,
};

enum {  // for _updateMask
    UPDATE_CONTENT  = 1,
    UPDATE_SHADOW   = 1 << 1,
    UPDATE_TEXTURE  = 1 << 2,
};

@interface MMovieOSD : NSObject
{
    NSSize _movieSize;          // real movie size
    NSRect _movieRect;          // display movie size
    unsigned int _updateMask;   // bit-mask of UPDATE_*

    NSShadow* _shadow;
    NSColor* _shadowColor;
    float _shadowBlur;         // for 640-width-of-movie
    float _shadowOffset;       // for 640-width-of-movie

    NSSize _contentSize;
    NSSize _drawingSize;
    unsigned int _hAlign;      // bit-mask of OSD_HALIGN_*
    unsigned int _vAlign;      // bit-mask of OSD_VALIGN_*
    float _hMargin;            // percentage of width
    float _vMargin;            // percentage of height

    GLuint _texName;
}

- (void)setMovieSize:(NSSize)size;
- (void)setMovieRect:(NSRect)rect;
- (float)autoSize:(float)defaultSize;

#pragma mark -
- (BOOL)hasContent;
- (void)clearContent;
- (void)updateContent;

#pragma mark -
- (void)setShadowColor:(NSColor*)shadowColor;
- (void)setShadowBlur:(float)shadowBlur;
- (void)setShadowOffset:(float)shadowOffset;
- (void)updateShadow;

#pragma mark -
- (unsigned int)hAlign;
- (unsigned int)vAlign;
- (void)setHAlign:(unsigned int)hAlign;
- (void)setVAlign:(unsigned int)vAlign;
- (BOOL)displayOnLetterBox;
- (float)hMargin;
- (float)vMargin;
- (void)setDisplayOnLetterBox:(BOOL)displayOnLetterBox;
- (void)setHMargin:(float)hMargin;
- (void)setVMargin:(float)vMargin;

#pragma mark -
- (NSSize)updateTextureSizes;
- (void)drawContent:(NSSize)texSize;
- (void)makeTexture:(CGLContextObj)glContext;
- (void)drawTexture:(NSRect)rect;

#pragma mark -
- (NSRect)drawingRectForViewBounds:(NSRect)viewBounds;
- (void)drawInViewBounds:(NSRect)viewBounds;

@end