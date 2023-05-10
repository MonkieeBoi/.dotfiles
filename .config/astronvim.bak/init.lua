return {
    -- Configure AstroNvim updates
    updater = {
        remote = "origin", -- remote to use
        channel = "stable", -- "stable" or "nightly"
        version = "latest", -- "latest", tag name, or regex search like "v1.*" to only do updates before v2 (STABLE ONLY)
        branch = "nightly", -- branch name (NIGHTLY ONLY)
        commit = nil, -- commit hash (NIGHTLY ONLY)
        pin_plugins = nil, -- nil, true, false (nil will pin plugins on stable only)
        skip_prompts = false, -- skip prompts about breaking changes
        show_changelog = true, -- show the changelog after performing an update
        auto_quit = false, -- automatically quit the current session after a successful update
        remotes = { -- easily add new remotes to track
            --     ["remote_name"] = "https://remote_url.come/repo.git", -- full remote url
            --     ["remote2"] = "github_user/repo", -- GitHub user/repo shortcut,
            --     ["remote3"] = "github_user", -- GitHub user assume AstroNvim fork
        },
    },

    -- Set colorscheme to use
    colorscheme = "nord",

    -- Diagnostics configuration (for vim.diagnostics.config({...})) when diagnostics are on
    diagnostics = {
        virtual_text = true,
        underline = true,
    },

    lsp = {
        -- customize lsp formatting options
        formatting = {
            -- control auto formatting on save
            format_on_save = {
                enabled = false, -- enable or disable format on save globally
                allow_filetypes = { -- enable format on save for specified filetypes only
                    -- "go",
                },
                ignore_filetypes = { -- disable format on save for specified filetypes
                    -- "python",
                },
            },
            disabled = { -- disable formatting capabilities for the listed language servers
                -- disable lua_ls formatting capability if you want to use StyLua to format your lua code
                -- "lua_ls",
            },
            timeout_ms = 1000, -- default format timeout
            -- filter = function(client) -- fully override the default formatting function
            --     return true
            -- end
        },
        -- enable servers that you already have installed without mason
        servers = {
            -- "pyright"
        },
    },

    -- Configure require("lazy").setup() options
    lazy = {
        defaults = { lazy = true },
        performance = {
            rtp = {
                -- customize default disabled vim plugins
                disabled_plugins = { "tohtml", "gzip", "matchit", "zipPlugin", "netrwPlugin", "tarPlugin" },
            },
        },
    },

    -- This function is run last and is a good place to configuring
    -- augroups/autocommands and custom filetypes also this just pure lua so
    -- anything that doesn't fit in the normal config locations above can go here
    polish = function()
        -- create an augroup to easily manage autocommands
        vim.api.nvim_create_augroup("autohidetabline", { clear = true })
        -- create a new autocmd on the "User" event
        vim.api.nvim_create_autocmd("User", {
            desc = "Hide tabline when only one buffer and one tab", -- nice description
            -- triggered when vim.t.bufs is updated
            pattern = "AstroBufsUpdated", -- the pattern si the name of our User autocommand events
            group = "autohidetabline", -- add the autocmd to the newly created augroup
            callback = function()
                -- if there is more than one buffer in the tab, show the tabline
                -- if there are 0 or 1 buffers in the tab, only show the tabline if there is more than one vim tab
                local new_showtabline = #vim.t.bufs > 1 and 2 or 1
                -- check if the new value is the same as the current value
                if new_showtabline ~= vim.opt.showtabline:get() then
                    -- if it is different, then set the new `showtabline` value
                    vim.opt.showtabline = new_showtabline
                end
            end,
        })
        vim.api.nvim_create_autocmd("VimLeave", {
            desc = "set cursor back to blinking line on leave",
            pattern = "*",
            command = "set guicursor=n:ver25-blinkon1"
        })
        -- Set up custom filetypes
        -- vim.filetype.add {
        --     extension = {
        --         foo = "fooscript",
        --     },
        --     filename = {
        --         ["Foofile"] = "fooscript",
        --     },
        --     pattern = {
        --         ["~/%.config/foo/.*"] = "fooscript",
        --     },
        -- }
    end,
    -- add new user interface icon
    icons = {
        VimIcon = "",
        ScrollText = "",
        GitBranch = "",
        GitAdd = "",
        GitChange = "",
        GitDelete = "",
    },
    -- modify variables used by heirline but not defined in the setup call directly
    heirline = {
        -- define the separators between each section
        separators = {
            left = { "", " " }, -- separator for the left side of the statusline
            right = { " █", "" }, -- separator for the right side of the statusline
            tab = { "", "" },
        },
        -- add new colors that can be used by heirline
        colors = function(hl)
            local get_hlgroup = require("astronvim.utils").get_hlgroup
            -- use helper function to get highlight group properties
            local comment_fg = get_hlgroup("Comment").fg
            hl.git_branch_fg = comment_fg
            hl.git_added = comment_fg
            hl.git_changed = comment_fg
            hl.git_removed = comment_fg
            hl.blank_bg = get_hlgroup("Folded").fg
            hl.file_info_bg = get_hlgroup("Visual").bg
            hl.nav_icon_bg = get_hlgroup("String").fg
            hl.nav_fg = hl.nav_icon_bg
            hl.folder_icon_bg = get_hlgroup("Error").fg
            return hl
        end,
        attributes = {
            mode = { bold = true },
        },
        icon_highlights = {
            file_icon = {
                statusline = false,
            },
        },
    },
}
