    let mapleader = ' '

" Basic Settings

    set encoding=utf-8
    set nu rnu
    set is
    syntax on
    set nocompatible
    set termguicolors

" Autocompletion

    set wildmode=longest,list,full
    filetype plugin on
    set omnifunc=syntaxcomplete#Complete
    " set shortmess+=c

" Tabs

    set tabstop=4
    set softtabstop=4
    set shiftwidth=4
    set expandtab
    set autoindent

" Splits

    set splitbelow splitright

" Clipboard

    " set clipboard+=unnamedplus


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
    require 'colorizer'.setup()
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

" Keybinding

    " CTRL-C doesn't trigger the InsertLeave autocmd . map to <ESC> instead.
    inoremap <c-c> <ESC>

    " Use <TAB> to select the popup menu:
    inoremap <expr> <Tab> pumvisible() ? "\<C-n>" : "\<Tab>"
    inoremap <expr> <S-Tab> pumvisible() ? "\<C-p>" : "\<S-Tab>"
