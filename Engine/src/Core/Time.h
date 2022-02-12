//
// Created by Ezra on 2022-02-12.
//

#pragma once

#include "Object.h"

namespace AsquiEngine {
    class Time : public Object {
    public:
        static float GetDeltaTime();

    private:
        inline static float s_DeltaTime;
        friend class Engine;
    };


}