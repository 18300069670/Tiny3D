/*******************************************************************************
 * This file is part of Mesh-converter (A mesh converter for Tiny3D Engine)
 * Copyright (C) 2015-2017  Answer Wong
 * For latest info, see https://github.com/asnwerear/Tiny3D
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

#include "mconv_command.h"
#include "mconv_settings.h"


namespace mconv
{
    bool Command::parse(int argc, char *argv[], Settings &settings)
    {
        printCommand(argc, argv);

        if (argc < 3)
        {
            printHelp();
            return false;
        }

        bool bShowHelp = false;
        String ext;

        int i = 0;
        for (i = 1; i < argc; ++i)
        {
            const char *arg = argv[i];
            int len = strlen(arg);
            if (len > 1 && arg[0] == '-')
            {
                if (arg[1] == '?')
                {
                    bShowHelp = true;
                }
                else if (arg[1] == 'v')
                {
                    settings.mVerbose = true;
                }
                else if (arg[1] == 'i')
                {
                    settings.mSrcType = parseFileType(argv[++i]);
                }
                else if (arg[1] == 'o')
                {
                    settings.mDstType = parseFileType(argv[++i]);
                    ext = argv[i];
                }
                else if (arg[1] == 'b')
                {
                    settings.mBoundType = parseBoundType(argv[++i]);
                }
                else if (arg[1] == 'm')
                {
                    settings.mFileMode = parseFileMode(argv[++i]);
                }
                else if (arg[1] == 'f')
                {
                    settings.mExtraPath = argv[++i];
                }
            }
            else if (settings.mSrcPath.length() == 0)
            {
                settings.mSrcPath = arg;
            }
            else if (settings.mDstPath.length() == 0)
            {
                settings.mDstPath = arg;
            }
        }

        if (bShowHelp || settings.mSrcPath.length() == 0)
        {
            printHelp();
            return false;
        }

        if (settings.mDstPath.length() == 0)
        {
            const String &srcPath = settings.mSrcPath;
            int pos = srcPath.rfind('.');
            settings.mDstPath = srcPath.substr(0, pos);
        }

        return true;
    }

    void Command::printCommand(int argc, char *argv[]) const
    {
        int i = 0;

        for (i = 1; i < argc; ++i)
        {
            if (i > 1)
                printf(" ");
            printf(argv[i]);
        }

        printf("\n");
    }

    void Command::printHelp() const
    {
        printf("Usage: mesh-conv.exe [options] <input> [<output>]\n");
        printf("\n");
        printf("Options:\n");
        printf("-?       : Display this help information.\n");
        printf("-i <type>: Set the type of the input file to <type>\n");
        printf("\t<type> : This type should be \"FBX\" (fbx), \"t3b\" (Tiny3D binary), \"t3t\" (Tiny3D text), \"DAE\" (dae) or \"OGRE\" (mesh).\n");
        printf("-o <type>: Set the type of the output file to <type>\n");
        printf("\t<type> : This type should be \"tmb\" (Tiny3D binary), \"tmt\" (Tiny3D text) or \"t3d\" (both binary and text).\n");
        printf("-b <type>: Set the type of the bounding box to <type>\n");
        printf("\t<type> : This type should be \"sphere\" or \"aabb\".\n");
        printf("-m <type>: This type should control file mode.\n");
        printf("\t<type> : This type should be \"shared\" or \"original\".\n");
        printf("\t              shared - Merge different meshes in one *.fbx file into one model file and all meshes share one vertex buffer.\n");
        printf("\t              original - Maintain meshes original structure.\n");
        printf("-f <filename>: This option is material file when input file type is OGRE.\n");
        printf("-v       : Verbose: print additional progress information\n");
        printf("\n");
        printf("<input>  : The filename of the file to convert.\n");
        printf("<output> : The filename of the converted file.\n");
        printf("\n");
        printf("<type>   : FBX, T3B (binary) or T3T (xml).\n");
    }

    FileType Command::parseFileType(const char *arg) const
    {
        FileType type = E_FILETYPE_AUTO;

        if (stricmp(arg, "fbx") == 0)
            type = E_FILETYPE_FBX;
        else if (stricmp(arg,"ogre") == 0)
            type = E_FILETYPE_OGRE;
        else if (stricmp(arg, T3D_BIN_MODEL_FILE_EXT) == 0)
            type = E_FILETYPE_T3B;
        else if (stricmp(arg, T3D_TXT_MODEL_FILE_EXT) == 0)
            type = E_FILETYPE_T3T;
        else if (stricmp(arg, "t3d") == 0)
            type = E_FILETYPE_T3D;

        return type;
    }

    BoundType Command::parseBoundType(const char *arg) const
    {
        BoundType type = E_BT_SPHERE;

        if (stricmp(arg, "sphere") == 0)
            type = E_BT_SPHERE;
        else if (stricmp(arg, "aabb") == 0)
            type = E_BT_AABB;

        return type;
    }

    FileMode Command::parseFileMode(const char *arg) const
    {
        FileMode mode = E_FM_ORIGINAL;

        if (stricmp(arg, "shared") == 0)
        {
            mode = E_FM_SHARE_VERTEX;
        }
        else if (stricmp(arg, "original") == 0)
        {
            mode = E_FM_ORIGINAL;
        }

        return mode;
    }
}
