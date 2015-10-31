class StoragePool{
	public:
		virtual ~StoragePool ();
		/**
		 * A função Allocate requisita uma quantidade de memória expressa em bytes 
		 * passada como argumento.
		 */
		virtual void * Allocate ( size_t ) = 0;
		/**
		 * A função Free recebe um ponteiro para uma região reservada e 
		 * a libera para uso posterior pelo GM.
		 */
		virtual void Free (void *) = 0;
};
