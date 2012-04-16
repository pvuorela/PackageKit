/*
 * Copyright (c) 2012 Daniel Nicoletti <dantti12@gmail.com>
 * Copyright (c) 2012 Matthias Klumpp <matthias@tenstral.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#ifndef APTCACHEFILE_H
#define APTCACHEFILE_H

#include <apt-pkg/cachefile.h>
#include <pk-backend.h>

class AptCacheFile : public pkgCacheFile
{
public:
    AptCacheFile(PkBackend *backend);
    ~AptCacheFile();

    /**
      * Inits the package cache returning false if it can't open
      */
    bool Open(bool withLock = false);

    /**
      * Closes the package cache
      */
    void Close();

    /**
      * Build caches
      */
    bool BuildCaches(bool withLock = false);

    /** This routine generates the caches and then opens the dependency cache
      * and verifies that the system is OK.
      */
    bool CheckDeps(bool AllowBroken = false);

    /** Shows a list of all broken packages together with their
     *  dependencies.  Similar to and based on the equivalent routine in
     *  apt-get.
     */
    void ShowBroken(bool Now);

    inline pkgRecords* GetPkgRecords() { buildPkgRecords(); return m_packageRecords; }

    /**
      * GetPolicy will build the policy object if needed and return it
      * @note This override if because the cache should be built before the policy
      */
    inline pkgPolicy* GetPolicy() { BuildCaches(); BuildPolicy(); return Policy; }

    /**
      * GetDepCache will build the dependency cache if needed and return it
      * @note This override if because the policy should be built before the dependency cache
      */
    inline pkgDepCache* GetDepCache() { BuildCaches(); BuildPolicy(); BuildDepCache(); return DCache; }

private:
    void buildPkgRecords();

    pkgRecords *m_packageRecords;
    PkBackend  *m_backend;
};

#endif // APTCACHEFILE_H