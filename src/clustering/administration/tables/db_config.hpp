// Copyright 2010-2014 RethinkDB, all rights reserved.
#ifndef CLUSTERING_ADMINISTRATION_TABLES_DB_CONFIG_HPP_
#define CLUSTERING_ADMINISTRATION_TABLES_DB_CONFIG_HPP_

#include <string>
#include <vector>

#include "errors.hpp"
#include <boost/shared_ptr.hpp>

#include "clustering/administration/database_metadata.hpp"
#include "containers/uuid.hpp"
#include "rdb_protocol/artificial_table/backend.hpp"
#include "rpc/semilattice/view.hpp"

class db_config_artificial_table_backend_t :
    public artificial_table_backend_t
{
public:
    db_config_artificial_table_backend_t(
            boost::shared_ptr< semilattice_readwrite_view_t<
                databases_semilattice_metadata_t> > _database_sl_view) :
        database_sl_view(_database_sl_view) { }

    std::string get_primary_key_name();
    bool read_all_primary_keys(
            signal_t *interruptor,
            std::vector<ql::datum_t> *keys_out,
            std::string *error_out);
    bool read_row(
            ql::datum_t primary_key,
            signal_t *interruptor,
            ql::datum_t *row_out,
            std::string *error_out);
    bool write_row(
            ql::datum_t primary_key,
            ql::datum_t new_value,
            signal_t *interruptor,
            std::string *error_out);

private:
    boost::shared_ptr< semilattice_readwrite_view_t<
        databases_semilattice_metadata_t> > database_sl_view;
};

#endif /* CLUSTERING_ADMINISTRATION_TABLES_DB_CONFIG_HPP_ */

