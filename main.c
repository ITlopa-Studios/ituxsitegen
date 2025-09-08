/*
 * Copyright (C) 2025 ITlopa
 *
 * This file is part of ItuxSiteGen.
 *
 * ItuxSiteGen is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * ItuxSiteGen is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include <locale.h>

int main(int argc, char **argv)
{
    if (setlocale(LC_ALL, "") == NULL) {
        fprintf(stderr, "Failed to set locale\n");
        PAUSE();
        return -1;
    }
    int argcounter = argc - 1;
    char* file_name = argv[0];
    if (argcounter < 1) {
        fprintf(stderr, "What site to generate?? Usage: %s <site name> and %s <site name> <flags> and other\n", file_name, file_name);
        PAUSE();
        return -1;
    }
    if (argcounter == 2 && strcmp(argv[1], "-rs") == 0) {
        char* site_name = argv[2];
        char default_theme[4096];
        char dark_theme[4096];
        char index_html[4096];
        char config_js[4096];
        snprintf(default_theme, sizeof(default_theme), "%s/themes/default.css", site_name);
        snprintf(config_js, sizeof(config_js), "%s/config.js", site_name);
        snprintf(index_html, sizeof(index_html), "%s/index.html", site_name);
        snprintf(dark_theme, sizeof(dark_theme), "%s/themes/dark.css", site_name);
        FILE* indexfile = fopen(index_html, "w");
        if (indexfile == NULL) {
            perror("Error opening index.html");
            PAUSE();
            return -1;
        }
        FILE* configfile = fopen(config_js, "w");
        if (configfile == NULL) {
            perror("Error opening config.js");
            fclose(indexfile);
            PAUSE();
            return -1;
        }

        FILE* theme1file = fopen(default_theme, "w");
        if (theme1file == NULL)
        {
            perror("Error opening default.css");
            fclose(indexfile);
            fclose(configfile);
            PAUSE();
            return -1;
        }

        fprintf(theme1file, "body {\n");
        fprintf(theme1file, "    background-color: #ffffff;\n");
        fprintf(theme1file, "    color: #000000;\n");
        fprintf(theme1file, "}\n");

        fprintf(theme1file, "h1, h2, h3, h4, h5, h6 {\n");
        fprintf(theme1file, "    text-align: center;\n");
        fprintf(theme1file, "}\n");

        FILE* theme2file = fopen(dark_theme, "w");
        if (theme2file == NULL)
        {
            perror("Error opening default.css");
            fclose(indexfile);
            fclose(configfile);
            fclose(theme1file);
            PAUSE();
            return -1;
        }

        fprintf(theme2file, "body {\n");
        fprintf(theme2file, "    background-color: #000000;\n");
        fprintf(theme2file, "    color: #ffffff;\n");
        fprintf(theme2file, "}\n");

        fprintf(theme2file, "h1, h2, h3, h4, h5, h6 {\n");
        fprintf(theme2file, "    text-align: center;\n");
        fprintf(theme2file, "}\n");

        char ConfigJSContext[9388];

        snprintf(ConfigJSContext, sizeof(ConfigJSContext), "let index_title = '%s';\nlet site_name = '%s';\nlet theme = 'dark';\nfunction CreateHeader(text, type) {\n     let header1 = document.createElement(`h${type}`);\n     header1.textContent = text;\n     document.body.appendChild(header1);\n}\nfunction loadStyle(styleName) {\n   const existingLink = document.getElementById('theme-style');\n  if (existingLink) {\n       existingLink.parentNode.removeChild(existingLink);\n    }\n     const link = document.createElement('link');\n  link.id = 'theme-style';\n      link.rel = 'stylesheet';\n      link.href = `themes/${styleName}.css`;\n    document.head.appendChild(link);\n}", site_name, site_name);

        fprintf(configfile, ConfigJSContext);

        fprintf(indexfile, "<head>\n    <script src=\"config.js\"></script>\n   <script>\n  loadStyle(theme);\n     </script>\n   <script>document.title = index_title;</script>\n</head>\n<body>\n    <script>\nCreateHeader(`Welcome to ${site_name}!`, '1');\n</script>\n</body>\n");

        fclose(configfile);
        fclose(indexfile);
        fclose(theme1file);
        fclose(theme2file);

        printf("Site %s is reseted!\n", site_name);

        PAUSE();

        return 0;
    }
    char* site_name = argv[1];
    // Check for the -gp flag
    if (argcounter == 3 && strcmp(argv[2], "-gp") == 0) {
        char* page_name = argv[3];
        char new_file_buf[4096];
        snprintf(new_file_buf, sizeof(new_file_buf), "%s/%s.html", site_name, page_name);

        FILE* new_page = fopen(new_file_buf, "w");
        if (new_page == NULL) {
            perror("Failed to create new page");
            return -1;
        }

        // Write the content of the new page
        fprintf(new_page, "<head>\n   <script src=\"config.js\"></script>\n   <script>\n      loadStyle(theme);\n      document.title = `%s | ${site_name}`;\n   </script>\n</head>\n<body>\n    <script>\n      CreateHeader(`%s of ${site_name} site.`, '1');\n   </script>\n</body>\n", page_name, page_name);

        fclose(new_page);
        fprintf(stdout, "Page %s is generated!\n", page_name);
        PAUSE();
        return 0;
    }
    char buffer_themes[4096];
    char buffer_scripts[4096];
    char default_theme[4096];
    char dark_theme[4096];
    char index_html[4096];
    char config_js[4096];
    MAKE_DIRECTORY(site_name);
    snprintf(buffer_themes, sizeof(buffer_themes), "%s/themes", site_name);
    MAKE_DIRECTORY(buffer_themes);
    snprintf(buffer_scripts, sizeof(buffer_scripts), "%s/scripts", site_name);
    MAKE_DIRECTORY(buffer_scripts);
    snprintf(default_theme, sizeof(default_theme), "%s/themes/default.css", site_name);
    snprintf(config_js, sizeof(config_js), "%s/config.js", site_name);
    snprintf(index_html, sizeof(index_html), "%s/index.html", site_name);
    snprintf(dark_theme, sizeof(dark_theme), "%s/themes/dark.css", site_name);
    FILE* indexfile = fopen(index_html, "w");
    if (indexfile == NULL) {
        perror("Error opening index.html");
        PAUSE();
        return -1;
    }
    FILE* configfile = fopen(config_js, "w");
    if (configfile == NULL) {
        perror("Error opening config.js");
        fclose(indexfile);
        PAUSE();
        return -1;
    }

    FILE* theme1file = fopen(default_theme, "w");
    if (theme1file == NULL)
    {
        perror("Error opening default.css");
        fclose(indexfile);
        fclose(configfile);
        PAUSE();
        return -1;
    }

    fprintf(theme1file, "body {\n");
    fprintf(theme1file, "    background-color: #ffffff;\n");
    fprintf(theme1file, "    color: #000000;\n");
    fprintf(theme1file, "}\n");

    fprintf(theme1file, "h1, h2, h3, h4, h5, h6 {\n");
    fprintf(theme1file, "    text-align: center;\n");
    fprintf(theme1file, "}\n");

    FILE* theme2file = fopen(dark_theme, "w");
    if (theme2file == NULL)
    {
        perror("Error opening default.css");
        fclose(indexfile);
        fclose(configfile);
        fclose(theme1file);
        PAUSE();
        return -1;
    }

    fprintf(theme2file, "body {\n");
    fprintf(theme2file, "    background-color: #000000;\n");
    fprintf(theme2file, "    color: #ffffff;\n");
    fprintf(theme2file, "}\n");

    fprintf(theme2file, "h1, h2, h3, h4, h5, h6 {\n");
    fprintf(theme2file, "    text-align: center;\n");
    fprintf(theme2file, "}\n");

    char ConfigJSContext[9388];

    snprintf(ConfigJSContext, sizeof(ConfigJSContext), "let index_title = '%s';\nlet site_name = '%s';\nlet theme = 'dark';\nfunction CreateHeader(text, type) {\n     let header1 = document.createElement(`h${type}`);\n     header1.textContent = text;\n     document.body.appendChild(header1);\n}\nfunction loadStyle(styleName) {\n   const existingLink = document.getElementById('theme-style');\n  if (existingLink) {\n       existingLink.parentNode.removeChild(existingLink);\n    }\n     const link = document.createElement('link');\n  link.id = 'theme-style';\n      link.rel = 'stylesheet';\n      link.href = `themes/${styleName}.css`;\n    document.head.appendChild(link);\n}", site_name, site_name);

    fprintf(configfile, ConfigJSContext);

    fprintf(indexfile, "<head>\n    <script src=\"config.js\"></script>\n   <script>\n  loadStyle(theme);\n     </script>\n   <script>document.title = index_title;</script>\n</head>\n<body>\n    <script>\nCreateHeader(`Welcome to ${site_name}!`, '1');\n</script>\n</body>\n");

    fclose(configfile);
    fclose(indexfile);
    fclose(theme1file);
    fclose(theme2file);

    printf("Site %s is created!\n", site_name);

    PAUSE();

    return 0;
}
