#pragma once

#ifndef VARLISTENER_HPP
#define VARLISTENER_HPP

namespace react {

    class VarListener {
    public:
        virtual void updateValue() = 0;
        virtual void updateLink() = 0;

    private:
    };

}

#endif // VARLISTENER_HPP
