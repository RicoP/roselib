PROC_SIG(debug,               cube     , (vector3 pos, vector3 size)                        , (pos, size)              )
PROC_SIG(debug,               cube     , (vector3 pos, vector3 size, vector3 color)         , (pos, size, color)       )
PROC_SIG(debug,               line     , (vector3 from, vector3 to)                         , (from, to)               )
PROC_SIG(debug,               line     , (vector3 from, vector3 to, vector3 color)          , (from, to, color)        )
PROC_SIG(debug,               sphere   , (vector3 pos, float radius)                        , (pos, radius)            )
PROC_SIG(debug,               sphere   , (vector3 pos, float radius, vector3 color)         , (pos, radius, color)     )

PROC_SIG(gfx,               resolution , (int w, int h)                                    , (w, h)                    )
PROC_SIG(gfx,               clear      , (int c)                                           , (c)                       )
PROC_SIG(gfx,               line       , (int x0, int y0, int x1, int y1, int c)           , (x0, y0, x1, y1, c)       )
PROC_SIG(gfx,               fill       , (int x, int y, int c)                             , (x, y, c)                 )
PROC_SIG(gfx,               putp       , (int x, int y, int c)                             , (x, y, c)                 )
PROC_SIG(gfx,               swap       , ()                                                , ()                        )
PROC_SIG(gfx,               draw_mesh  , (RHash mesh, RHash texture, vector3 pos), (mesh, texture, pos) )
PROC_SIG(gfx,               draw_mesh  , (RHash mesh, RHash texture, matrix4 mvt), (mesh, texture, mvt) )
FUNC_SIG(gfx, unsigned int, getp       , (int x, int y)                                    , (x, y)                    )

FUNC_SIG(asset,   RHash, mesh   , (const char* name)                           , (name)                    )
FUNC_SIG(asset,   RHash, texture, (const char* name)                           , (name)                    )

FUNC_SIG(random,   RHash, from_clock, ()      , ()          )
FUNC_SIG(random,   int,              nexti,      (RHash & rand, int min, int max)      , (rand, min, max)          )
FUNC_SIG(random,   float,            nextf,      (RHash & rand, float min, float max)  , (rand, min, max)          )

FUNC_SIG(ui,       bool,    button     , (const char * name)                               , (name)                    )

FUNC_SIG(ecs,    rose::Scene&,       scene      , ()                                  , ()                        )

FUNC_SIG(meta,   rose::MicroSystem&, system_data, ()                                  , ()                     )
PROC_SIG(meta,                            request_camera_ownership, ()                     , ()                     )

//TODO: get rid of input functions. We have a event system for that.
FUNC_SIG(input,    PadEvent,      pad,     (int player)                        , (player)                        )
FUNC_SIG(input,    PadEvent,      pad_raw, (int player)                        , (player)                        )
FUNC_SIG(input,    vector2,       stick,   ()                                  , ()                        )
FUNC_SIG(input,    bool,          action,  ()                                  , ()                        )
