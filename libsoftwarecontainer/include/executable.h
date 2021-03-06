/*
 *
 * Copyright (C) 2016-2017 Pelagicore AB
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

#pragma once

#include "softwarecontainer-common.h"

namespace softwarecontainer {

class Executable
{
public:
    // A function to be executed in the container
    typedef std::function<int ()> ExecFunction;

    /**
     * @brief Executes a commandline.
     */
    virtual bool execute(ExecFunction function,
                               pid_t *pid,
                               const EnvironmentVariables &variables = EnvironmentVariables(),
                               int stdin = -1,
                               int stdout = -1,
                               int stderr = 2) = 0;

    /**
     * @brief Executes a function.
     */
    virtual bool execute(const std::string &commandLine,
                               pid_t *pid,
                               const EnvironmentVariables &variables = EnvironmentVariables(),
                               const std::string &workingDirectory = "/",
                               int stdin = -1,
                               int stdout = 1,
                               int stderr = 2) = 0;
};

} // namespace softwarecontainer
