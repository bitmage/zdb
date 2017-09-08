/*
 * ZDB Copyright 2017 Regents of the University of Michigan
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy
 * of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef ZDB_SRC_LOCATION_H
#define ZDB_SRC_LOCATION_H

#include <maxminddb.h>
#include <cstdint>

#include "record.h"

namespace zdb {

class GeoIP {
 public:
  GeoIP();
  GeoIP(const std::string& mmdb_path);
  ~GeoIP();

  bool open(const std::string& mmdb_path);
  bool is_open() const { return m_open; };

  // Returns true on success
  bool populate_atom(zsearch::LocationAtom* atom, uint32_t ip) const;

 private:
  mutable MMDB_s m_db;
  bool m_open = false;

  DISALLOW_COPY_ASSIGN(GeoIP);
};

}  // namespace zdb

#endif /* ZDB_SRC_LOCATION_H */
