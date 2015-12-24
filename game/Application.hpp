#pragma once

class Application {

public:
                                Application(int argc, char **argv);

    void                        run(void);

private:
    void                        runLocal(void);
    void                        runServer(void);
    void                        runClient(void);
};
