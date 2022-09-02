" Basic Settings

    set encoding=utf-8
    set nu rnu
    set is
    syntax on
    set nocompatible
    filetype plugin on
    set termguicolors " up here because of nvim-colorizer

" Autocompletion

    set wildmode=longest,list,full

" Tabs

    set tabstop=4
    set softtabstop=4
    set shiftwidth=4
    set expandtab
    set autoindent

" Splits

    set splitbelow splitright

" Plugins

call plug#begin(stdpath('data') . '/plugged')

    Plug 'shaunsingh/nord.nvim'
    Plug 'itchyny/lightline.vim'
    Plug 'numToStr/Comment.nvim'
    Plug 'norcalli/nvim-colorizer.lua'
    " Plug 'JoosepAlviste/nvim-ts-context-commentstring'

call plug#end()

lua << EOF
    require('Comment').setup()
    require'colorizer'.setup()
    -- require'nvim-treesitter.configs'.setup {
    --     context_commentstring = {
    --     enable = true
    --     }
    -- }
EOF

" Theming

    let g:lightline = {'colorscheme': 'nord'}
    set laststatus=2
    colorscheme nord

" Clipboard

    " set clipboard+=unnamedplus

" Keybinding

    let mapleader = ' '
