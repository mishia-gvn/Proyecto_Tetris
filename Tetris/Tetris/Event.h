#pragma once

struct Event
{
    enum Type
    {
        FALL,
        LINE_CLEAR,
        SPAWN
    };

    Type type;
    float triggerTime;

    Event(Type type, float triggerTime) {
        this->type = type;
        this->triggerTime = triggerTime;
    }
};