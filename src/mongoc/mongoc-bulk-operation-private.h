/*
 * Copyright 2014 MongoDB, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef MONGOC_BULK_OPERATION_PRIVATE_H
#define MONGOC_BULK_OPERATION_PRIVATE_H


#include "mongoc-array-private.h"
#include "mongoc-client.h"


BSON_BEGIN_DECLS


struct _mongoc_bulk_operation_t
{
   char                   *database;
   char                   *collection;
   mongoc_client_t        *client;
   mongoc_write_concern_t *write_concern;
   bool                    ordered;
   bool                    omit_n_modified;
   mongoc_array_t          commands;
   uint32_t                hint;
   uint32_t                n_modified;
   uint32_t                n_upserted;
   uint32_t                n_matched;
   uint32_t                n_removed;
   uint32_t                n_inserted;
   uint32_t                offset;
   bson_t                 *upserted;
   bson_t                 *write_errors;
   bson_t                 *write_concern_errors;
};


typedef enum
{
   MONGOC_BULK_COMMAND_INSERT = 1,
   MONGOC_BULK_COMMAND_UPDATE,
   MONGOC_BULK_COMMAND_DELETE,
} mongoc_bulk_command_type_t;


typedef struct
{
   int type;
   union {
      struct {
         bson_t *document;
      } insert;
      struct {
         uint8_t   upsert : 1;
         uint8_t   multi  : 1;
         bson_t   *selector;
         bson_t   *document;
      } update;
      struct {
         uint8_t  multi : 1;
         bson_t  *selector;
      } delete;
   } u;
} mongoc_bulk_command_t;


mongoc_bulk_operation_t *_mongoc_bulk_operation_new (mongoc_client_t              *client,
                                                     const char                   *database,
                                                     const char                   *collection,
                                                     uint32_t                      hint,
                                                     bool                          ordered,
                                                     const mongoc_write_concern_t *write_concern);


BSON_END_DECLS


#endif /* MONGOC_BULK_OPERATION_PRIVATE_H */
