local autocmd = vim.api.nvim_create_autocmd

-- Auto resize panes when resizing nvim window
-- autocmd("VimResized", {
--   pattern = "*",
--   command = "tabdo wincmd =",
-- })

autocmd("VimLeave", {
  pattern = "*",
  command = "silent !echo -ne '\e[5 q'",
})
