#ifndef SF_INPUT_H
#define SF_INPUT_H

namespace sf_input
{
    enum class SF_Key
    {
        null = 0,

        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        RETURN,

        end
    };

    class SF_Input
    {
    public:
        SF_Input();
        ~SF_Input();

        bool get_key_state(SF_Key button);
        void get_mouse_position(float &x, float &y);
        void set_mouse_position(float x = 0, float y = 0);

    protected:
        void set_key_state(SF_Key key, bool state);
        unsigned short get_key_code(SF_Key button);

        unsigned short key_lenght = static_cast<unsigned short>(SF_Key::end);
        bool *key_states = 0x0;

    };
};

#endif