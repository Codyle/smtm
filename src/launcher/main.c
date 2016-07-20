/*
 * Copyright (C) 2016 HE Yaowen <he.yaowen@hotmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <Windows.h>
#include <getopt/getopt.h>
#include <smtm/smtm.h>

#define OPTS_SHORT_STRING "hv"

static const struct option opt_define[] = {
        { "version", no_argument, NULL, 'v' },
        { "help", no_argument, NULL, 'h' },
        { NULL, 0, NULL, 0 }
};

static void display_version(void) {
    fprintf(stdout, "%s\n", SMTM_VERSION);
}

static void display_help(void) {
    fprintf(stdout, "usage: smtm [-v|--version] [-h|--help] FILE\n");
}

int main(int argc, char** argv) {
    char* filename;

    do {
        optopt = getopt_long(argc, argv, OPTS_SHORT_STRING, opt_define, &optind);

        switch (optopt) {
            case 'v':
                display_version();
                return 0;
            case 'h':
                display_help();
                return 0;
            default:
                /* You won't actually get here */
                break;
        }
    } while (optopt != -1);

    /* If FILE argument is missing */
    if (optind >= argc) {
        display_help();
        return 0;
    }

    filename = argv[optind];

    if (_access(filename, 0) == -1) {
        fprintf(stderr, "file '%s' not exists.\n", filename);
        return -1;
    }

    if (_access(filename, 4) == -1) {
        fprintf(stderr, "file '%s' is not readable.\n", filename);
        return -1;
    }

    return smtm_run_script(filename);
}