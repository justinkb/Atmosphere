/*
 * Copyright (c) Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stratosphere.hpp>
#include "fs_filesystem_accessor.hpp"
#include "fs_file_accessor.hpp"
#include "fs_directory_accessor.hpp"
#include "fs_mount_utils.hpp"
#include "fs_user_mount_table.hpp"

namespace ams::fs {

    namespace impl {

        Result GetFileTimeStampRawForDebug(FileTimeStampRaw *out, const char *path) {
            impl::FileSystemAccessor *accessor;
            const char *sub_path;
            R_TRY(impl::FindFileSystem(std::addressof(accessor), std::addressof(sub_path), path));

            R_TRY(accessor->GetFileTimeStampRaw(out, sub_path));

            return ResultSuccess();
        }

    }

    Result GetFileTimeStamp(FileTimeStamp *out, const char *path) {
        fs::FileTimeStampRaw raw;
        AMS_FS_R_TRY(impl::GetFileTimeStampRawForDebug(std::addressof(raw), path));

        static_assert(sizeof(raw) == sizeof(*out));
        std::memcpy(out, std::addressof(raw), sizeof(raw));
        R_SUCCEED();
    }

}
