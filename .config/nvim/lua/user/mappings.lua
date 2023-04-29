-- Mapping data with "desc" stored directly by vim.keymap.set().
--
-- Please use this mappings table to set keyboard mapping since this is the
-- lower level configuration and more robust one. (which-key will
-- automatically pick-up stored data by this setting.)
return {
  -- first key is the mode
  n = {
    -- second key is the lefthand side of the map
    -- mappings seen under group name "Buffer"
    ["<leader>bn"] = { "<cmd>tabnew<cr>", desc = "New tab" },
    ["<leader>bD"] = {
      function()
        require("astronvim.utils.status").heirline.buffer_picker(function(bufnr) require("astronvim.utils.buffer").close(bufnr) end)
      end,
      desc = "Pick to close",
    },
    -- tables with the `name` key will be registered with which-key if it's installed
    -- this is useful for naming menus
    -- ["<leader>b"] = { name = "Buffers" },
    -- quick save
    ["<C-s>"] = { ":w <cr>", desc = "Save File" },  -- change description but the same command
    ["<A-i>"] = { "<cmd>ToggleTerm direction=float<cr>", desc = "ToggleTerm float" },
    ["<A-h>"] = { "<cmd>ToggleTerm size=15 direction=horizontal<cr>", desc = "ToggleTerm horizontal split" },
    ["<A-v>"] = { "<cmd>ToggleTerm size=50 direction=vertical<cr>", desc = "ToggleTerm vertical split" },
    ["<leader>x"] = { function() require("astronvim.utils.buffer").close() end, desc = "Close buffer" },
    ["<C-c>"] = { "<cmd> %y+ <CR>", desc = "Copy whole file" },
  },
  t = {
    -- setting a mapping to false will disable it
    -- ["<esc>"] = false,
    ["<A-i>"] = { "<cmd>ToggleTerm direction=float<cr>", desc = "ToggleTerm float" },
    ["<A-h>"] = { "<cmd>ToggleTerm size=15 direction=horizontal<cr>", desc = "ToggleTerm horizontal split" },
    ["<A-v>"] = { "<cmd>ToggleTerm size=50 direction=vertical<cr>", desc = "ToggleTerm vertical split" },
    ["<C-x>"] = { vim.api.nvim_replace_termcodes("<C-\\><C-N>", true, true, true), desc = "Escape terminal mode" },
  },
  i = {
    ["<C-h>"] = { "<Left>", desc = "move left" },
    ["<C-l>"] = { "<Right>", desc = "move right" },
    ["<C-j>"] = { "<Down>", desc = "move down" },
    ["<C-k>"] = { "<Up>", desc = "move up" },
  }
}
