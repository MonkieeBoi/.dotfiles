local opt = vim.opt
local g = vim.g
local autocmd = vim.api.nvim_create_autocmd

-------------------------------------- options ------------------------------------------

opt.clipboard = "unnamed"

-- Indenting
opt.shiftwidth = 4
opt.tabstop = 4
opt.softtabstop = 4

-- Numbers
opt.relativenumber = true

-- enable nvim intro
opt.shortmess:remove "I"

-- don't go to previous/next line with h,l,left arrow and right arrow
opt.whichwrap:remove "<>[]hl"

-------------------------------------- autocmds ------------------------------------------

autocmd("VimLeave", {
  pattern = "*",
  command = "set guicursor=n:ver25-blinkon1",
})
