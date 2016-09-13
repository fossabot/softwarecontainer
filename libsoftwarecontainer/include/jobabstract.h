/*
 * Copyright (C) 2016 Pelagicore AB
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
 * BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 *
 * For further information see LICENSE
 */
#ifndef SOFTWARECONTAINER_JOBABSTRACT
#define SOFTWARECONTAINER_JOBABSTRACT

#include "libsoftwarecontainer.h"

namespace softwarecontainer {
/**
 * Abstract class for jobs which get executed inside a container
 */
class JobAbstract
{
protected:
    LOG_SET_CLASS_CONTEXT(SoftwareContainerLib::getDefaultContext());

public:
    static constexpr int UNASSIGNED_STREAM = -1;

    JobAbstract(SoftwareContainerLib &lib);
    virtual ~JobAbstract();

    void captureStdin();
    void setOutputFile(const std::string &path);
    void captureStdout();
    void captureStderr();

    int wait();

    int stdout();
    int stderr();
    int stdin();

    pid_t pid();

    /**
     * That method always returns true as soon as the start() method has been called, even if the command fails to start,
     * since we don't know if the exec() occurring after the fork into the container actually succeeds...
     */
    bool isRunning();
    void setEnvironnmentVariable(const std::string &key, const std::string &value);
    void setEnvironnmentVariables(const EnvironmentVariables &env);

protected:
    EnvironmentVariables m_env;
    SoftwareContainerLib &m_lib;
    pid_t m_pid = 0;
    int m_stdin[2] = {UNASSIGNED_STREAM, UNASSIGNED_STREAM};
    int m_stdout[2] = {UNASSIGNED_STREAM, UNASSIGNED_STREAM};
    int m_stderr[2] = {UNASSIGNED_STREAM, UNASSIGNED_STREAM};
};
}

#endif // SOFTWARECONTAINER_JOBABSTRACT
