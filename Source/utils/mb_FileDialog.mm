#import <Cocoa/Cocoa.h>
#include <string>

std::string mb_MacOpenFileDialog() {
    @autoreleasepool {
        NSOpenPanel* panel = [NSOpenPanel openPanel];
        [panel setCanChooseFiles:YES];
        [panel setCanChooseDirectories:NO];
        [panel setAllowsMultipleSelection:NO];
        
        NSInteger result = [panel runModal];
        if (result == NSModalResponseOK) {
            NSURL* fileURL = [panel URL];
            return std::string([[fileURL path] UTF8String]);
        }
    }
    return "";
}