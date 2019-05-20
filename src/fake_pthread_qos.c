/*

    Workaround for:

        dyld: lazy symbol binding failed: Symbol not found: _pthread_attr_set_qos_class_np
          Referenced from: /Volumes/Otter Browser Installer/Otter Browser.app/Contents/MacOS/../Frameworks/QtWebKit.framework/Versions/5/QtWebKit
          Expected in: /usr/lib/libSystem.B.dylib

        dyld: Symbol not found: _pthread_attr_set_qos_class_np
          Referenced from: /Volumes/Otter Browser Installer/Otter Browser.app/Contents/MacOS/../Frameworks/QtWebKit.framework/Versions/5/QtWebKit
          Expected in: /usr/lib/libSystem.B.dylib

    Due to running on Mac OS X 10.9 when:

        `pthread_attr_set_qos_class_np` is marked as `__API_AVAILABLE(macos(10.10), ios(8.0))`


    Compile via:

        clang -Wl,-dylib -o fake_pthread_qos.dylib fake_pthread_qos.c

    Use via, for example:

        DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=fake_pthread_qos.dylib /<path>/Otter\ Browser.app/Contents/MacOS/Otter\ Browser



    Allows running the app (modulo a bunch of unknown selector messages & Qt paint messages) enough to load a web page.

    Eventually another missing function is hit (after clicking a link?):

        dyld: lazy symbol binding failed: Symbol not found: _dispatch_queue_attr_make_with_qos_class
          Referenced from: /Users/philip/Development/otter-browser-related/Otter Browser.orig.app/Contents/MacOS/../Frameworks/QtWebKit.framework/Versions/5/QtWebKit
          Expected in: flat namespace

        dyld: Symbol not found: _dispatch_queue_attr_make_with_qos_class
          Referenced from: /Users/philip/Development/otter-browser-related/Otter Browser.orig.app/Contents/MacOS/../Frameworks/QtWebKit.framework/Versions/5/QtWebKit
          Expected in: flat namespace

        Trace/BPT trap: 5

    Due to:

      * `dispatch_queue_attr_make_with_qos_class()` is marked as SDK macOS 10.10+.
        <https://developer.apple.com/documentation/dispatch/1453028-dispatch_queue_attr_make_with_qo>

      * However return type `dispatch_queue_attr_t` is marked as SDK macOS 10.6+, so it might be possible to just
        return the first argument `attr`.
        <https://developer.apple.com/documentation/dispatch/dispatch_queue_attr_t?language=objc>


    Note: The OS & browser message dialogs after a crash cause another crash so you may need to run:

              #trash ~/Library/Saved\ Application\ State/org.otter-browser.otter-browser.savedState
              #trash ~/Library/Preferences/otter # (or mv/rename)

          But I suspect this is due to includedd Qt being 5.9 rather than 5.6?

 */


/*

   Based on:

     int pthread_attr_set_qos_class_np(pthread_attr_t *__attr, qos_class_t __qos_class, int __relative_priority);

   via <https://github.com/apple/darwin-libpthread/blob/master/pthread/qos.h#L81>

   Also:

     "@return [...] Zero if successful, otherwise an errno value."
 */

int pthread_attr_set_qos_class_np(void * arg0, void * arg1, int arg2) {
  return 0;
}
