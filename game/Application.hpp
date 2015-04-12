#pragma once

class Application {

public:
                                Application(int argc, char **argv);
                                ~Application(void);

    // 42 norme
                                Application(void)                   = delete;
                                Application(const Application &)    = delete;
    Application &               operator=(const Application &)      = delete;
    //

    void                        run(void);

private:
    void                        runLocal(void);
    void                        runServer(void);
    void                        runClient(void);
};
