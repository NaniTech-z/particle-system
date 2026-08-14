#pragma once

class Timer {
    public:
        Timer();

        void update();

        float getDeltaTime() const;
        float getElapsedTime() const;

    private:
        float previousTime;
        float deltaTime;
        float elapsedTime;
};