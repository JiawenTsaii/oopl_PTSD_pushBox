#ifndef PHASE_HPP
#define PHASE_HPP

class Phase {
public:
    virtual ~Phase() = default;
    virtual void Update() = 0;
};

#endif //PHASE_HPP