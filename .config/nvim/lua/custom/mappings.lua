---@type MappingsTable
local M = {}

M.general = {
  n = {
    [";"] = { ":", "enter command mode", opts = { nowait = true } },
  },
  v = {
    ["<S-Tab>"] = {"<gv", "unindent line"},
    ["<Tab>"] = {">gv", "indent line"},
  }
}

-- more keybinds!

return M
