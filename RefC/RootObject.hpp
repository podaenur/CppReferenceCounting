//
//  RootObject.hpp
//  RefC
//
//  Created by Ilya Kulebyakin on 10/11/15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#import "Util.hpp"


#define Retain(ptr) ptr->retain(); ptr->makeSafe((RootObject**)&ptr);
#define Release(ptr) if (ptr->release()) { delete ptr; ptr = nullptr; } else { ptr->makeUnsafe((RootObject**)&ptr);}
#define Autorelease(ptr) ptr->autorelease(); ptr->makeUnsafe((RootObject**)&ptr);

// TODO: Make default for initialization
#define Safify(ptr) ptr->makeSafe((RootObject**)&ptr);

#define CSO(ptr, constructor) ptr = constructor; ptr->makeSafe((RootObject**)&ptr);

namespace RefCount {
    class RootObject {
        int _refCount;
        bool _autorelease;
        RootObject*** _selfPtrs;
        int _selfPtrsCount = 0;
        int _selfPtrsCapacity = 0;
        
        void freePointers();
    public:
        RootObject();
        virtual ~RootObject();
        
        void retain();
        bool release();
        void autorelease();
        void makeSafe(RootObject** ptr);
        void makeUnsafe(RootObject** ptr);
        
        bool drain();
    };
}

